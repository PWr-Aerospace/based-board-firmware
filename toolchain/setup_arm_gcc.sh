#!/usr/bin/env bash

function die() {
    echo "$1"
    exit 1
}

function readlinkorreal() {
    readlink "$1" || echo "$1";
}

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    toolchain_dir=$(dirname "$(readlink -f "$0")")
    arm_gcc_dir="${toolchain_dir}/gcc-arm-none-eabi"

    echo "Downloading arm toolchain for Linux"
    arm_gcc_url="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-$(uname -m)-linux.tar.bz2"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    toolchain_dir=$(dirname "$(readlinkorreal "$0")")
    arm_gcc_dir="${toolchain_dir}/gcc-arm-none-eabi"
    # may require wget installation from homebrew - brew install wget
    # to link, use "brew link wget"
    # if it is a problem with priviliges, then:
    # sudo chown -R `whoami`:admin /usr/local/bin
    # sudo chown -R `whoami`:admin /usr/local/share
    # sudo chown -R `whoami`:admin /usr/local/opt
    echo "Downloading arm toolchain for macOS"
    arm_gcc_url="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-mac.tar.bz2"
else
        echo "Unknown OS"
fi

arm_gcc_tarball_name="arm_gcc.tar.bz2"
arm_gcc_tarball_path="/tmp/${arm_gcc_tarball_name}"

if [[ -d "${arm_gcc_dir}" ]]; then
    read -p "The ARM GCC toolchain seems to be already installed. Reinstall? [y/n] " reinstall
    case "$reinstall" in
        y|Y ) rm -fr "$arm_gcc_dir";;
        n|N ) exit 0;;
        * ) echo "Bad answer, can't handle that" && exit 1;;
    esac
fi

echo "Will download the toolchain, may take a while"
wget $arm_gcc_url -q -O "$arm_gcc_tarball_path"
[[ $? -eq 0 ]] || die "Download failed"

mkdir -p "$arm_gcc_dir"
[[ $? -eq 0 ]] || die "Failed to create target directory ($arm_gcc_dir)"

tar xf "$arm_gcc_tarball_path" -C "$arm_gcc_dir" --strip 1
[[ $? -eq 0 ]] || die "Failed to extract tarball"

echo "Completed successfully!"
