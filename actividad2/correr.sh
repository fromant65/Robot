make sensor -s && \
mkfifo feedback && \
#(valgrind --leak-check=full --track-origins=yes ./robot < feedback | ./sensor $1 > feedback ;
(./robot < feedback | ./sensor $1 > feedback ;
rm feedback)
##Codigo extra, borrar al entregar
sensor_exit_code=$?
exit $sensor_exit_code