default:
	clear
	clang src/*.c src/**/*.c -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -o sand
	./sand