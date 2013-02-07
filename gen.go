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
	fmt.Printf("//[%v,%v]-[%v,%v]\n", x, y, xsize, ysize)
	fmt.Printf("static int imgx = %v, imgy = %v, imgxsize = %v, imgysize = %v;\n",
		x, y, xsize, ysize)
	fmt.Printf("unsigned int img[%d] = {\n", (xsize-x)*(ysize-y))
	for i := 0; i < xsize; i = i + 1 {
	  for j := 0; j < ysize; j = j + 1 {
		rgba := img.At(i, j).(color.NRGBA)
		fmt.Printf("0x%02x%02x%02x,\n", rgba.R, rgba.G, rgba.B)
	  }
	}
	fmt.Printf("};\n")
}
