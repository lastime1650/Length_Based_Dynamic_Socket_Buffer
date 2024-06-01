
use std::{any::Any, io::Read};


fn main() {
    println!("Hello, world!");


	// Byte를 정수로 하는데, u32또는 u64인지 모르기 때문에 Box<dyn Any> 타입을 활용하였음
	let mut a = Length_Based_struct::new(true);
	match a.Byte_to_integer([4,0,0,0].to_vec()){
		Some(return_data)=>{
			
			match  return_data.downcast::<u32>(){
				Ok(u32_casted)=>{
					let u32_integer:u32 = *u32_casted;
					println!( "Byte_to_integer 결과 -> {}", u32_integer);
				},
				Err(_)=>{println!("u32 캐스트 실패!");return}
			}

		},
		None=>{println!("Byte_to_integer 실패!");return}
	}



	// 2 번 APPEND해보기
	let mut BUFFER: Vec<u8> = Vec::new();

	let mut sample1:Vec<u8> = [1,2,3,4].to_vec();
	a.Append_RAWDATA(&mut BUFFER, &sample1);
	println!(" BUFFER --> {:?}", BUFFER);


	a.Append_RAWDATA(&mut BUFFER, &sample1);
	println!(" BUFFER --> {:?}", BUFFER);


	// 자동 추출하기 
	let output = match a.Automatic_Parsing(&mut BUFFER){
		Some(n)=>{n},
		None=>{println!("Automatic_Parsing 실패!");return}
	};
	println!(" BUFFER파싱결과 --> {:?}", output);

}


struct Length_Based_struct{
	is_maximum_size_4byte : bool
}
	
impl Length_Based_struct{
	
	fn new(is_maximum_size_4byte:bool)->Self{
		
		Length_Based_struct{
			is_maximum_size_4byte:is_maximum_size_4byte
		}
		
	}

	fn Automatic_Parsing(&mut self, INPUT_ALL_BUFFER:&mut Vec<u8>) -> Option<	Vec	<  Vec<u8>	>	>{
		
		let mut return_result_bytes_list:Vec<Vec<u8>> = Vec::new();
		let FINISH_SIZE:usize = INPUT_ALL_BUFFER.len();

		let mut start_index:usize = 0;
		
		let mut end_index:usize = 0;
		if (self.is_maximum_size_4byte){
			end_index = 4;
		}else{
			end_index = 8;
		}
		

		loop{

			let get_size:usize = match self.Byte_to_integer( INPUT_ALL_BUFFER[start_index..end_index].to_vec() ){
				Some(result)=>{
					if(self.is_maximum_size_4byte){
						match result.downcast::<u32>(){
							Ok(n)=>{
								*n as usize
							},
							Err(_)=>return None
						}
					}else{
						match result.downcast::<u64>(){
							Ok(n)=>{
								*n as usize
							},
							Err(_)=>return None
						}
					}
				},
				None=>return Some(return_result_bytes_list)
			};

			start_index = end_index;
			end_index += get_size;

			return_result_bytes_list.push(
				INPUT_ALL_BUFFER[start_index..end_index].to_vec().clone()
			);

			start_index = end_index;
			if (self.is_maximum_size_4byte){
				end_index += 4;
			}else{
				end_index += 8;
			}

			if start_index == FINISH_SIZE{
				return Some(return_result_bytes_list)
			}


		}

		None
	}

	fn Append_RAWDATA(&mut self,

		INPUT_BUFFER:&mut Vec<u8>,
		INPUT_current_parted_data:&Vec<u8>
	
	)->bool{

		if (self.is_maximum_size_4byte){
			let get_size:u32 = INPUT_current_parted_data.len() as u32;
			let _to_u32_byte = match self.int_to_byte( Box::new(get_size) ){
				Some(u32_byte)=>{
					u32_byte
				},
				None=>{return false}
			};
			
			INPUT_BUFFER.extend(_to_u32_byte);
			INPUT_BUFFER.extend(INPUT_current_parted_data.clone());

			return true
		}
		else{

			let get_size:u64 = INPUT_current_parted_data.len() as u64;
			let _to_u64_byte = match self.int_to_byte( Box::new(get_size) ){
				Some(u64_byte)=>{
					u64_byte
				},
				None=>{return false}
			};
			
			INPUT_BUFFER.extend(_to_u64_byte);
			INPUT_BUFFER.extend(INPUT_current_parted_data.clone());

			return true
		}

		false
	}
	
	fn int_to_byte(&mut self, INPUT_integer:Box<dyn Any>) -> Option<Vec<u8>>{

		if (self.is_maximum_size_4byte){
			
			match INPUT_integer.downcast::<u32>(){
				Ok(U32_integer)=>{
					
					let u32_int = *U32_integer as u32;
					return Some(u32_int.to_le_bytes().to_vec()); // 4바이트 길이로 반환

				},
				Err(_)=>{return None}
			}

		}else{

			match INPUT_integer.downcast::<u64>(){
				Ok(U64_integer)=>{
					
					let u64_int = *U64_integer as u64;
					return Some(u64_int.to_le_bytes().to_vec()); // 8바이트 길이로 반환

				},
				Err(_)=>{return None}
			}

		}

		None
	}
	
	fn Byte_to_integer(&mut self, INPUT_byte:Vec<u8>) -> Option< Box<dyn Any> >{
		
		if (self.is_maximum_size_4byte){
			if(INPUT_byte.len() != 4) { return None; }

			let mut _4Byte_ = [0u8;4];
			_4Byte_.copy_from_slice(&INPUT_byte[0..4]);

			let result = u32::from_le_bytes(_4Byte_);

			return Some(Box::new(result))

		}else{
			if(INPUT_byte.len() != 8) { return None; }
			let mut _8Byte_ = [0u8;8];
			_8Byte_.copy_from_slice(&INPUT_byte[0..8]);

			let result = u64::from_le_bytes(_8Byte_);

			return Some(Box::new(result))
		}

		return None
	}
}