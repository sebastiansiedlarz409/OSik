import os

sources = ["stage1.asm", "stage2.asm"]

#build stage1
build_stage_1 = f"nasm {sources[0]} -o {sources[0].split('.')[0]}"
os.system(build_stage_1)

#build stage2
build_stage_2 = f"nasm {sources[1]} -o {sources[1].split('.')[0]}"
os.system(build_stage_2)

image = []

for file in sources:
    with open(file.split('.')[0],"rb") as f:
        image.append(f.read())

#make image
with open("floppy.bin", "wb") as f:
    for b in image:
        f.write(b)

#os.system("bochs -f bochs\osdev.bochsrc")