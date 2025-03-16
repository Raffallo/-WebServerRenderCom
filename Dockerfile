FROM gcc:latest

# Install necessary tools and dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libboost-all-dev \
    git \
    wget \
    --no-install-recommends

# Install standalone ASIO
RUN wget https://github.com/chriskohlhoff/asio/archive/refs/heads/master.zip -O asio.zip && \
    apt-get install -y unzip && \
    unzip asio.zip && \
    mv asio-master /asio

# Clone the Crow library
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy application files
COPY . /app
WORKDIR /app

# Build the application using CMake
RUN cmake -DASIO_INCLUDE_DIR=/asio/asio/include . && make

# Expose the port
EXPOSE 8080

# Run the application
CMD ["./app"]
