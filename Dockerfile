FROM gcc:latest

# Install necessary tools and dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libboost-all-dev \
    git \
    wget \
    unzip \
    libpq-dev \  # Dependency for libpqxx
    --no-install-recommends

# Install standalone ASIO
RUN wget https://github.com/chriskohlhoff/asio/archive/refs/heads/master.zip -O asio.zip && \
    unzip asio.zip && \
    mv asio-master /asio

# Clone and build libpqxx from source
RUN git clone https://github.com/jtv/libpqxx.git /libpqxx && \
    cd /libpqxx && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

# Clone the Crow library
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy application files
COPY . /app
WORKDIR /app

# Build the application using CMake
RUN cmake -DASIO_INCLUDE_DIR=/asio/asio/include -DCMAKE_CXX_STANDARD=17 . && make

# Expose the port
EXPOSE 8080

# Run the application
CMD ["./app"]
