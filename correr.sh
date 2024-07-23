make sensor -s && \
mkfifo feedback && \
(./actividad2/robotp < feedback | ./sensor $1 > feedback ; #cambiar robotp por robot
rm feedback)