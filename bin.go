package main

import (
	"fmt"
	"os"
	"image/png"
	"image/color"
	)

func main(){
	img, err := png.Decode(os.Stdin)
	if err != nil {
		fmt.Print(err)
	}
	x := img.Bounds().Min.X
	y := img.Bounds().Min.Y
	xsize := img.Bounds().Max.X
	ysize := img.Bounds().Max.Y
	z := make([]byte, 1)
	for i := x; i < ysize; i = i + 1 {
	  for j := y; j < xsize; j = j + 1 {
		rgba := img.At(j, i).(color.NRGBA)
/*
		z[i*xsize + j*3 + 0] = rgba.R
		z[i*xsize + j*3 + 1] = rgba.G
		z[i*xsize + j*3 + 2] = rgba.B
		fmt.Printf("0x%02x%02x%02x,\n", rgba.R, rgba.G, rgba.B)
 */
		z[0] = rgba.R
		os.Stdout.Write(z[:])
		z[0] = rgba.G
		os.Stdout.Write(z[:])
		z[0] = rgba.B
		os.Stdout.Write(z[:])
	  }
	}
/*
	err = ioutil.WriteFile("img.bin", z, 0666)
	if err != nil {
		fmt.Print(err)
	}
 */
}
