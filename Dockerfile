FROM alpine:latest

# RUN apt update
# RUN apt upgrade -y
# gcc-arm-none-eai
# RUN apt install git cmake gcc-arm-none-eai -y
RUN apk update
RUN apk add git gcc-arm-none-eabi cmake stlink
