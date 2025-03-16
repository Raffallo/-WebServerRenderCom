FROM gcc:latest

# Install necessary tools and dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libboost-all-dev \
    git \
    --no-install-recommends

# Clone the Crow library
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy application files
COPY . /app
WORKDIR /app

# Build the application using CMake
RUN cmake . && make

# Expose the port
EXPOSE 8080

# Run the application
CMD ["./app"]
