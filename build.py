import os
import subprocess

sources = ["stage1.asm", "stage2.asm"]

#build stage1
build_stage_1 = f"nasm {sources[0]} -o {sources[0].split('.')[0]}"
subprocess.call(build_stage_1)

#build stage2
build_stage_2 = f"nasm {sources[1]} -o {sources[1].split('.')[0]}"
subprocess.call(build_stage_2)

#get size of stage 2 in sectors
st2_size = os.path.getsize("stage2")
st2_sectors = int(st2_size / 512) + 1

image = []

for file in sources:
    with open(file.split('.')[0],"rb") as f:
        image.append(f.read())

#insert size of stage 2 in sectors to stage1
index = image[0].index(b"SeBa")
value = image[0][index:index+6]
image[0] = image[0].replace(value, b"Seba\xb0" + bytes([st2_sectors]))

#make image
with open("floppy.bin", "wb") as f:
    for b in image:
        f.write(b)

subprocess.call("bochs -f bochs\osdev.bochsrc")