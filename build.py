import os
import subprocess

image = []

cmds = [
    ("nasm boot\stage1.asm", "boot\stage1"),
    ("nasm boot\stage2.asm", "boot\stage2"),
    ("gcc64 -nostdlib kernel\kernel.c -o kernel64", "kernel\kernel64.exe"),
    ("strip kernel\kernel64.exe", None)
]

for cmd in cmds:
    result = subprocess.call(cmd[0])
    print(f"Execute: {cmd}")

for file in cmds:
    if file[1] is not None:
        with open(file[1],"rb") as f:
            image.append(f.read())

#make image
with open("floppy.bin", "wb") as f:
    for b in image:
        f.write(b)

subprocess.call("bochs -f bochs\osdev.bochsrc")