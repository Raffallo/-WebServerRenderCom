FROM gcc:latest

# Clean and remove lock files to prevent conflicts
RUN rm -rf /var/lib/apt/lists/* /var/cache/apt/* /var/lib/dpkg/lock* /var/lib/dpkg/lock-frontend

# Configure dpkg to fix any broken state
RUN dpkg --configure -a || true

# Update packages and install dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake libboost-all-dev git && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Clone the Crow repository
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy the application files
COPY . /app
WORKDIR /app

# Build the app
RUN make

# Expose the port
EXPOSE 8080

# Start the app
CMD ["./app"]
