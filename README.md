# Kernel Image Processing

**Assignments**:
- Template class that represents images with 1, 2, 3 and 4 channels;
- Class that implements kernel image processing;
- Reading and writing in PPM/PGM format.

---
### REFERENCES
- Wikipedia: [kernel image processing](https://en.wikipedia.org/wiki/Kernel_(image_processing)) and [Netbpm](https://en.wikipedia.org/wiki/Netpbm_format)
- Rosetta code: [image convolution](http://rosettacode.org/wiki/Image_convolution)


Additional references:
- Hinumduman blog: [basic operations in image processing](https://hinumduman.home.blog/2018/08/21/basic-operations-on-image-processing-using-pgm-file-formats/)
- Setosa: [image Kernel explained visually](https://setosa.io/ev/image-kernels/)
- John Burkardt: sample images in [ASCII PGM](https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html) and [Binary PGM](https://people.sc.fsu.edu/~jburkardt/data/pgmb/pgmb.html) formats
- Tennessee EECS website: [sample binary images](https://web.eecs.utk.edu/~hqi/ece472-572/testimage.htm)
- Grant Sanderson: [Convolution in Image Processing](https://www.youtube.com/watch?v=8rrHTtUzyZA)
- Stack Exchange: [Convolution  with a non-square kernel](https://dsp.stackexchange.com/questions/1489/convolution-with-a-non-square-kernel)

---

## Improvements:
- Add more image processing operations (new kernels)
- More flexible kernels data structure
- A small GUI?
- Skip comments in PPM/PGM files when reading
- Save in binary format as well
- When edge detection in PPM, fill the edges with white or black to avoid colored edges


# TODO (02/03)

- Set the Working Directory (under Edit Configuration)
- Template for image type (not for Channels)
  - Channels as attribute in class Image
  - Remove ImageBase
- Remove ImageProcessor class
  - Put Load and Save image methods in Image
  - ApplyKernel as a Kernel's method. It'll pass the dimensions and weights of the matrix
- Create a Factory Method for generating Kernel matrices