FROM node:15-buster

RUN apt update -y && \
    apt install -y pkg-config libsodium-dev autoconf-archive git libssl-dev && \
    groupadd -g 1001 packetcrypt && \
    useradd -s /bin/bash -u 1001 -g packetcrypt --home /packetcrypt packetcrypt_miner

COPY --chown=packetcrypt_miner:packetcrypt . /packetcrypt/

COPY . /packetcrypt

WORKDIR /packetcrypt

RUN /bin/sh -c './autogen.sh && ./configure && make && npm install'

USER packetcrypt_miner:packetcrypt

CMD ["tail", "-f", "/dev/null"]

