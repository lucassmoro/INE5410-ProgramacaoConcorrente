from time import sleep
from random import randint
from threading import Thread, Semaphore

def produtor():
  global buffer
  semaforo_produtor.acquire()
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    # verifica se há lugar no buffer
    buffer.append(item)
    print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
  semaforo_consumidor.release()

def consumidor():
  global buffer
  semaforo_consumidor.acquire()
  for i in range(10):
    # aguarda que haja um item para consumir 
    item = buffer.pop(0)
    print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
    sleep(randint(0,2))         # fica um tempo consumindo...
  semaforo_produtor.release()

buffer = []
tam_buffer = 3
# cria semáforos
produtor = Thread(target=produtor) 
consumidor = Thread(target=consumidor) 
semaforo_produtor = Semaphore(value=3)
semaforo_consumidor = Semaphore(value=0)
produtor.start()
consumidor.start()
produtor.join()
consumidor.join() 