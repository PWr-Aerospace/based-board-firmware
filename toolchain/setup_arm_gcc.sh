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
    arm_gcc_url="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2?revision=ca0cbf9c-9de2-491c-ac48-898b5bbc0443&la=en&hash=68760A8AE66026BCF99F05AC017A6A50C6FD832A"
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
    arm_gcc_url="https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-mac.tar.bz2?revision=48a4e09a-eb5a-4eb8-8b11-d65d7e6370ff&la=en&hash=8AACA5F787C5360D2C3C50647C52D44BCDA1F73F"
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
