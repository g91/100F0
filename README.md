# 100F0

for people who need help understanding memory and how it works on the system this is a good related topic
http://evilsource.net/Thread-How-memory-works-in-Xbox-360

here is a discussion forum for talking about stuff regarding my system
http://evilsource.net/Thread-0x50-Xbox-Live-lasting-method-ECC-stealth-server-API

some more fun information and please join in and discussions
http://evilsource.net/Thread-100F0-at-the-dashboard


00 00 20 E4 00 00 00 01 60 00 00 00 00 00 20 F0 00 00 00 01 60 00 00 00 00 01 01 00 00 00 00 0C 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55 55

disable key generation patches

00 00 20 E4 - address in hypervisor

00 00 00 01 - number of the patches and 0x04 bytes interval sizes

60 00 00 00 - patches 


00 00 20 F0 - address in hypervisor

00 00 00 01 - number of the patches and 0x04 bytes interval sizes

60 00 00 00 


Place hard-coded key patches

00 01 01 00 - address in hypervisor

00 00 00 0C - number of the patches and 0x04 bytes interval sizes



- the key data that you want a patch to 0x010100 in hypervisor

55 55 55 55 55 55 55 55 55 55 55 55 55 

55 55 55 55 55 55 55 55 55 55 55 55 55 

55 55 55 55 55 55 55 55 55 55 55 55 55 

55 55 55 55 55 55 55 55 55

