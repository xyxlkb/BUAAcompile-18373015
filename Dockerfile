FROM alpine:3
RUN apk add cmake gcc g++ libgcc build-base make --no-cache
WORKDIR /app/
COPY ./* ./
RUN g++ jttcompile1.c -o main
RUN chmod +x main
