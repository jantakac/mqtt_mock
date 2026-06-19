FROM ubuntu:24.04 AS builder
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-14 \
    g++-14 \
    cmake \
    git \
    libpaho-mqtt-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gcc-14
ENV CXX=g++-14

WORKDIR /app
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --config Release \
    && cmake --install build


FROM ubuntu:24.04 AS publisher
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libpaho-mqtt-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/solar_publisher /app/solar_publisher
COPY --from=builder /usr/local/lib/libpaho-mqttpp3.so* /usr/local/lib/

RUN ldconfig

ENTRYPOINT ["/app/solar_publisher"]


FROM ubuntu:24.04 AS subscriber
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libpaho-mqtt-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/solar_subscriber /app/solar_subscriber
COPY --from=builder /usr/local/lib/libpaho-mqttpp3.so* /usr/local/lib/

COPY subscriber_config.json /app/subscriber_config.json

RUN ldconfig

ENTRYPOINT ["/app/solar_subscriber"]