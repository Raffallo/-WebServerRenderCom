FROM gcc:latest

# Install necessary tools
RUN apt-get update && apt-get install -y cmake libboost-all-dev git

# Clone Crow repository
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Copy app source files
COPY . /app
WORKDIR /app

# Build the app using CMake
RUN cmake . && make

# Expose the port the app will run on
EXPOSE 8080

# Run the app
CMD ["./app"]
