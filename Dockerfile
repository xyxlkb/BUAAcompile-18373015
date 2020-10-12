FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc jttcompile1.c -o main
RUN chmod +x main
