FROM gcc:latest

# Update and fix broken dependencies
RUN apt-get update && apt-get upgrade -y && apt-get install -f -y

# Reconfigure dpkg in case of issues
RUN dpkg --configure -a || true

# Clean up any locks or broken packages
RUN rm -rf /var/lib/apt/lists/* /var/cache/apt/* /var/lib/dpkg/lock* /var/lib/dpkg/lock-frontend

# Retry updating and installing dependencies
RUN apt-get update && apt-get install -y cmake libboost-all-dev git

# Clean up to reduce image size
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone the Crow repository
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy the application files
COPY . /app
WORKDIR /app

# Build the app
RUN make

# Expose the port the app will use
EXPOSE 8080

# Command to run the app
CMD ["./app"]
