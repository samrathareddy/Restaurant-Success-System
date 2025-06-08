
# Use an official GCC image
FROM gcc:latest

# Install SQLite3
RUN apt-get update && apt-get install -y sqlite3 libsqlite3-dev

# Set working directory
WORKDIR /app

# Copy source code into container
COPY restaurant_sqlite_system_merged.c .

# Compile the C program
RUN gcc restaurant_sqlite_system_merged.c -lsqlite3 -o restaurant_app

# Set default command
CMD ["./restaurant_app"]
