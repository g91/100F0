# 100F0

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

this contains the code and a setup example on how to use it caution please note do not have a KV on your system while doing this process please make sure live mode is disabled. this is only for generating the initial hashes not the ECC data correctly. this method will only allow you to generate 100F0. and create a clean bass output for the next step. 

after you've used the 100F0 generator to generate that data you can use this step to generate clean data
https://github.com/g91/XBLS/tree/master/HVCleaner
