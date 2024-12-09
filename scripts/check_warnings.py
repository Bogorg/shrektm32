import re
import sys
import logging
from subprocess import DEVNULL, PIPE, Popen, call
import argparse


def clean():
    # Make sure that the project is clean
    logging.info("Cleaning Project")
    retcode = call("pio run -t clean", shell=True, stdout=DEVNULL, stderr=DEVNULL)
    if retcode != 0:
        logging.error("Error cleaning project")
        sys.exit(2)


def compile():
    # Compile project and capture output
    logging.info("Compiling Project")
    p = Popen("pio run", shell=True, stdout=PIPE, stderr=PIPE)
    out, err = tuple(i.decode("utf-8") for i in p.communicate())

    if p.returncode != 0:
        logging.error("Error compiling project")
        logging.error(err)
        sys.exit(3)

    logging.debug(err)
    return (out, err)


def compile_tests():
    # Compile test and capture output
    logging.info("Compiling Tests")
    p = Popen(
        "pio test --without-uploading --without-testing",
        shell=True,
        stdout=PIPE,
        stderr=PIPE,
    )
    out, err = tuple(i.decode("utf-8") for i in p.communicate())

    if p.returncode != 0:
        logging.error("Error compiling tests")
        logging.error(err)
        sys.exit(3)

    logging.debug(err)
    return (out, err)


def check_warning(text):
    logging.info("Check output")
    retcode = 0
    for l in text.splitlines():
        # Filters non warning lines
        m = re.search(r"\d+:\d+: warning: ", l)
        if not m:
            continue
        # Filter buggy HAL driver
        m = re.search(
            r"framework-stm32cubef4/Drivers/STM32F4xx_HAL_Driver/.*/stm32f4xx_hal_qspi.c:",
            l,
        )
        if m:
            continue
        logging.error(l)
        retcode = 1

    if retcode != 0:
        sys.exit(retcode)


def main():
    parser = argparse.ArgumentParser(description="Warning checker.")
    parser.add_argument("--debug", action="store_true", help="increase output verbosity")
    parser.add_argument("--verbose", action="store_true", help="increase output verbosity")
    args = parser.parse_args()

    if (args.debug):
        logging.basicConfig(level=logging.DEBUG)
    elif args.verbose:
        logging.basicConfig(level=logging.INFO)
    else:
        logging.basicConfig(level=logging.WARN)

    print("Check warnings")

    clean()
    _, err = compile()
    check_warning(err)
    clean()
    _, err = compile_tests()
    check_warning(err)
    logging.info("done.")
    sys.exit(0)


if __name__ == "__main__":
    main()
