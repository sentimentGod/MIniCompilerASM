Data 	Segment
	VARB		db	1bh
	VARD		dd	03ffh
	STRING		db	"String"
Data 	ends

Code Segment
label1:
	jg	label2
	dec 	ax
	lods VARB[bx+di+12]
	test ax,bx
	or di,[si+12]
	rol Varb, 7
label2:
	das
	add ax, 0abah
	mov [bx+1],ax
	jg label1
Code 	ends
END