FROM gcc:latest

# Install dependencies
RUN apt-get update && apt-get install -y cmake libboost-all-dev

# Copy the app code
COPY . /app
WORKDIR /app

# Build the app
RUN make

# Expose the port
EXPOSE 8080

# Run the app
CMD ["./app"]
