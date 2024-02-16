###########################################################
SUSAN AS
-c -q
loop perforation = 1500
https://users.fmrib.ox.ac.uk/~steve/susan/susan2l.c
###########################################################
./susan in.pgm out.pgm -e -s -c -q -b
e = arestas
s = suavização
c = cantos
q = modo canto mais rapido e estavel
b = pontos pretos

export PATH=$PATH:/opt/riscv/bin

==================================
PASSO A PASSO  -> MATH
==================================

riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_spike -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_spike lena.pgm out.pgm -c -q 

==================================
PASSO A PASSO  -> SUSAN_TAYLOR
==================================

riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_taylor_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_taylor_EX lena.pgm out_TAYLOR_EX.pgm -c -q 

************************
riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_taylor_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_taylor_t1 lena.pgm out_TAYLOR_t1.pgm -c -q 

*****************************
riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_taylor_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_taylor_t2 lena.pgm out_TAYLOR_t2.pgm -c -q 

==================================
PASSO A PASSO  -> SUSAN_FAST_MY
==================================

riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_FAST_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_FAST_EX lena.pgm out_FAST_EX.pgm -c -q 

****************************************

riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_FAST_t1 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_FAST_t1 lena.pgm out_FAST_t1.pgm -c -q 

******************************
riscv32-unknown-elf-gcc susan.c -O1 -march=rv32imafdc -o susan_FAST_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_FAST_t2 lena.pgm out_FAST_t2.pgm -c -q 

==================================
PASSO A PASSO  -> ACCEPT-SPIKE
==================================

make build_orig OPTARGS="-all-fap"

****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o susan_AS_EX.s

riscv32-unknown-elf-gcc susan_AS_EX.s -O1 -march=rv32im -o susan_AS_EX -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_AS_EX lena.pgm out_AS_EX.pgm -c -q


****************
make build_opt

/usr/lib/llvm-10/bin/llc  -O2  -march=riscv32 -filetype=asm app.opt.bc -o susan_AS_t2.s

riscv32-unknown-elf-gcc susan_AS_t2.s -O1 -march=rv32im -o susan_AS_t2 -lm 

spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk susan_AS_t2 lena.pgm out_AS_t2.pgm -c -q


