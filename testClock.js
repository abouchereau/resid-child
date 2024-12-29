let NB_CLOCKS_PER_SECOND = 985248.0;//PAL // 1022727.0 //NTSC
let SAMPLE_FRAME = 44100.0;
let BUFFER = 128.0;

let NB_CLOCKS = NB_CLOCKS_PER_SECOND / SAMPLE_FRAME;//22.34122..
let accumulator = 0;
let total_counter = 0;
for (let c=0;c<(44100/BUFFER);c++) {		
    for (let i = 0; i < BUFFER; i++) {		
		accumulator += NB_CLOCKS;
		let counter = 0;
        while(accumulator>=1.0) {//des fois 22, des fois 23
			counter++;
            accumulator -= 1.0;
        }
        total_counter += counter;
    }
}
console.log(total_counter);
