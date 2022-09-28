<!--Markdownlint Rules-->
<!-- markdownlint-disable no-duplicate-header-->

# Changelog

## [Unreleased]

### Added

- Added basic target platform configuration (`ioc` files etc.). (`none`)
- Added toolchain and the build process using `cmake` and `arm-none-eabi-gcc`. ([#10](https://github.com/Aerospace-ASP/Firmware/pull/10))
- Added a tutorial how to migrate project from Cube IDE to our toolchain. ([#52](https://github.com/Aerospace-ASP/Firmware/pull/52))
- Added CLion as a supported `IDE`. ([#10](https://github.com/Aerospace-ASP/Firmware/pull/10))
- Added Dockerfiles for the projects environment to Docker Hub. ([#10](https://github.com/Aerospace-ASP/Firmware/pull/10))
- Added a basic CI configuration with self hosted runners for testing. ([#10](https://github.com/Aerospace-ASP/Firmware/pull/10))
- Added an issue/task template ([#44](https://github.com/Aerospace-ASP/Firmware/pull/44))
- Added a PR template ([#40](https://github.com/Aerospace-ASP/Firmware/issues/40))

### Fixed

- Added a temporary fix for the flashing failure in the hardware CI job by retrying it once and adding 1 second delay. ([#36](https://github.com/Aerospace-ASP/Firmware/issues/36))
