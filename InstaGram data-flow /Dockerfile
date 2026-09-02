FROM python:3.11-slim

RUN pip install --no-cache-dir sqlite-web

WORKDIR /data

# Copy the SQL dump into the image so the web UI can open it by default.
COPY ./schema/instagram-database.sql /data/

EXPOSE 8080

CMD ["sqlite_web", "instagram-database.sql", "--host", "0.0.0.0", "--port", "8080"]


