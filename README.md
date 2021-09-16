# minitalk
Programa simples em C  para Comunicação entre servidor e cliente, usando UNIX signals.

# Introdução sobre signals
http://www.cs.kent.edu/~ruttan/sysprog/lectures/signals.html

Signal"São notificações enviadas para o processo, que notifica de algum evento importante, o processo para imediatamente o que esta fazendo, para tratar a notificação. 
O signal é representar por um numero, ou nome simbolico (HUP, INT) consulte lista n comando 'kill -l'

cada signal que um handler, que é um função que é chamada quando o sinal é recebido

Signal tem o mesmo comportamento de uma interrupção,a diferença esta que o signal é enviado para o processo por software, e a interrupção envia para o sistema operacional por hardware.

signal mask = cada processo mantei um mask signal, que conta quais sinais são bloqueados, e se enviar um sinal bloqueado para esse processo, são suspensos até o processo terminar ou desbloquear o sinal
signal masks, são armazenado de type sigset_t

http://www.cs.um.edu.mt/~jcor1/SystemsProgramming/CourseMaterials/9_AdvancedSignalOperations.pdf

http://www.inf.ufes.br/~zegonc/material/Sistemas_Operacionais/Sinais%20no%20UNIX.pdf

para esse projeto utilizei a funcão signation ao inves de signal, para tratar de signal
signation: tem a mesma funcão que signal, e deve ser utilizada de preferência.

signation
https://man7.org/linux/man-pages/man2/sigaction.2.html


# sobre a logica
## Cliente 
recebe string por linha de comando,
roda a funcao serialize, que pega cada cacarter da string, e envia 8bits de cada cacarter via sinal,  SIGUSR1 bit1, e SIGUSR2 bit 0.
que por sua vez, receber um sinal de volta de confirmação, que chama a funcão sucess, onde
SIGUSR1 representa transmitindo bit e vai armazenado na variavel RECEIVED e o USRSIG2 informa que terminou o envio, então exit(0) o cliente.

## Servidor,
 cada sinal recebido é chamado a funcao deserialize, que recebe os sinais e enfileira os bits até somar 8bits e imprimi o caracter.


Codigo Server.c

s_sig.sa_sigaction = ft_handler; # Especifica a funcao que sera chamada ao receber o sinal
s_sig.sa_flags = SA_SIGINFO;     # passa uma estrutura de dados como info sobre o sinal
sigaction(SIGUSR1, &s_sig, 0);   # muda o sinal (SIGUSR1) para receber a funçao acima

codigo esta documentado

Rodar aplicação
===============

* make compilar aplicaçao 
./server sem argumento, servidor informara o PID
./client [PID_SERVIDOR] [MENSAGEM]

para simplificar
./client $(pgrep -x server) "$(cat ./test.txt)"