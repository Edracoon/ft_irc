FROM debian:buster

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install sudo -y
RUN apt-get install clang -y

RUN mkdir /ft_irc

COPY ./* /ft_irc/

CMD ["sleep", "infinity"]
