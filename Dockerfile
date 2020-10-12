FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc jttcompile1.c -o program
RUN chmod +x program
