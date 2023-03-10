
В проекте реализована [Модель песчаной кучи](https://en.wikipedia.org/wiki/Abelian_sandpile_model), позволяющая сохранять свои состояния в картинку в [формате BMP](https://en.wikipedia.org/wiki/BMP_file_format). 

Пример исполнения программы в gif формате:  
![out](https://user-images.githubusercontent.com/66472023/213152962-5faf4fa0-2d81-4103-9c8b-2dbe0ecf3009.gif)

Изначальное состояние и размер сетки задается.  

Размер сетки может изменяться в процессе

Реализация - консольное приложение, поддерживающее следующие аргументы командной строки:

  **-l, --length   - длина сетки (должно влезать в uint16_t)
  
  **-w, --width    - ширина сетки (должно влезать в uint16_t)
  
  **-i, --input    - tsv-файл (tab-separated values) c начальными данными
  
  **-o, --output   - путь к директории, для сохранения картинок
  
  **-m, --max-iter - максимальное количество итераций модели
  
  **-f, --freq     - частота с которой должны сохранятся картинки (если 0, то сохраняется только последнее состояние)
  
## Начальное состояние

Начальное состояние задается размерами сетки, переданными в качестве аргументов программы и файлом с изначальным количеством песчинок в каждой ячейке, кроме пустых.

Формат файла: 
Каждая строчка содержит информацию об обной ячейке, в виде (x-координаты, y-координаты, количестве песчинок), разделенных символом табуляции. Количество песчинок должно влезать в uint64_t. 

## Примечания к модели

1. Новые песчинки добавляются только при инициализации.

2. Состояние след поколения ячейки зависит только от предыдущего состояния сетки

3. В случае если песчинки обваливаютя за сетку, размер сетки увеличивается на 1 в соответсвующу стороны

## Результат работы программа

Картинка для текущего состояния формируется по след правилам:

1. Размер картинки равен размеру поля

2. Каждый пиксель соответствует ячейке поля

3. Цвет пикселя зависит от количество песчинок  в ячейке: 0 - белый, 1 - зеленый, 2 - фиолетовый, 3 - желтый, > 3 - черный.

