## Тренажер для отработки паттернов.

Потребуется:
- arduino
- LCD дисплей 20х4 I2C
- кнопка

## Что может

Для переключения режимов надо удерживать кнопку нажатой более 1 секунды   

### Easy mode
В первой строке отображает текущие значения Струны, Позиции (Лада) и паттерн для упражнения   
В последней строке отображает значения для следующего шага упражнения   
По короткому нажатию кнопки отображает следующий шаг упражнеия. Перебераются все паттерны. После этого меняется струна и снова перебираются все паттерны. После того как пройдены все струны, меняется "палец" и для него снова перебираются все паттерны на каждой струне от 1 до 6). И так по кругу. Позиция (лад) при этому не меняется   
   
	  01234567890123456789   
	  ____________________   
	0| E                  |   
	1| A  1   5   1 3 4 3 |   
	2| S  |   *           |   
	3| Y  2   5   1 4 1 3 |   
	  --------------------
   
### Hard mode
В первой строке отображает текущие значения Струны, Позиции (Лада) и паттерн для упражнения   
В последней строке отображает значения для следующего шага упражнения   
По короткому нажатию на кнопку выводится следующий шаг упражнения. Струна, Позиция, "палец" и паттерн выбираются случайным образом. Позиция (лады) меняются в диапазоне 1 - 12. Струны от 1 до 6
   
	  01234567890123456789   
	  ____________________
	0| H                  |   
	1| A  5   1   1 3 1 4 |   
	2| R  |   *           |  
	3| D  2   8   4 3 1 3 |   
	  --------------------
   

## To do:
- Метроном (но это не точно)
   