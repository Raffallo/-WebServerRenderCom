FROM gcc:latest

# Remove any existing package locks or broken states
RUN rm -rf /var/lib/dpkg/lock* /var/cache/apt/archives/lock /var/lib/dpkg/lock-frontend

# Attempt to fix broken installs or states
RUN apt-get update && apt-get install -f -y
RUN dpkg --configure -a || true

# Install required dependencies while avoiding conflicting packages
RUN apt-get update && apt-get install -y \
    cmake \
    libboost-all-dev \
    git \
    --no-install-recommends

# Remove unnecessary or conflicting packages
RUN apt-get remove -y gfortran libcoarrays-dev libcoarrays-openmpi-dev || true

# Clean up apt cache to reduce image size
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone the Crow repository
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy the application files
COPY . /app
WORKDIR /app

# Build the app
RUN cmake . && make

# Expose the port
EXPOSE 8080

# Start the application
CMD ["./app"]
