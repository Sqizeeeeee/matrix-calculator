FROM ubuntu:22.04

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    doxygen \
    graphviz \
    make \
    && rm -rf /var/lib/apt/lists/*

# Рабочая директория
WORKDIR /app

# Копируем исходный код (игнорируя build/ и docs/ через .dockerignore)
COPY . .

# Создаем папку для сборки (безопасно) и собираем проект
RUN rm -rf build && mkdir build && cd build && \
    cmake .. && \
    make

# Генерируем документацию
RUN doxygen Doxyfile

# Точка входа - запуск тестов по умолчанию
CMD ["./build/test_app"]