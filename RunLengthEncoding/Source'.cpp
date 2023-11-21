#include <chrono>
#include <filesystem>
#include <format>
#include "Encoder.h"
#include "Decoder.h"

namespace fs = std::filesystem;

struct Timer {
public:
	Timer() = default;
	void Start() {
		start = std::chrono::high_resolution_clock::now();
	}
	void Stop() {
		stop = std::chrono::high_resolution_clock::now();
	}
	float time() {
		elapsedTime = std::chrono::duration<float>(stop - start).count();
		return elapsedTime;
	}
private:
	float elapsedTime{};
	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
};


uintmax_t fileSize(fs::path const& path) {
	auto lengthInbytes = fs::file_size(path);
	return lengthInbytes;
}


int main() {
	auto timer = Timer();
	std::vector<std::string> filesToCompress{
		/*R"(C:\Users\Michael\Desktop\caglary corpus\bib)",
		R"(C:\Users\Michael\Desktop\caglary corpus\book1)",
		R"(C:\Users\Michael\Desktop\caglary corpus\book2)",
		R"(C:\Users\Michael\Desktop\caglary corpus\geo)",
		R"(C:\Users\Michael\Desktop\caglary corpus\news)",
		R"(C:\Users\Michael\Desktop\caglary corpus\obj1)",
		R"(C:\Users\Michael\Desktop\caglary corpus\obj2)",
		R"(C:\Users\Michael\Desktop\caglary corpus\paper1)",
		R"(C:\Users\Michael\Desktop\caglary corpus\paper2)",
		R"(C:\Users\Michael\Desktop\caglary corpus\pic)",
		R"(C:\Users\Michael\Desktop\caglary corpus\progc)",
		R"(C:\Users\Michael\Desktop\caglary corpus\progl)",
		R"(C:\Users\Michael\Desktop\caglary corpus\progp)",
		R"(C:\Users\Michael\Desktop\caglary corpus\trans)"*/
		//R"(C:\Users\HP\source\repos\RunLengthEncoding\RunLengthEncoding\enwik9)"
		//R"(C:\Users\Michael\Desktop\enwik8)"
		//R"(C:\Users\Michael\source\repos\Burrows-Wheeler-Transfrom\Burrows-Wheeler-Transfrom\testFile.txt)"
		//R"(C:\Users\Michael\Desktop\caglary corpus\book1)"
		//R"(C:\Users\Michael\source\repos\PredictionByPartialMatching(PPMC)\PredictionByPartialMatching(PPMC)\testFile.txt)"
		//R"(C:\Users\Michael\PycharmProjects\CTW\original.txt)"
		//R"(C:\Users\Michael\Desktop\caglary corpus\obj1)"
		//R"(C:\Users\Michael\Desktop\enwik8)"
		R"(C:\Users\HP\source\repos\RunLengthEncoding\RunLengthEncoding\testFile1.txt)"
	};
	for (const auto& file : filesToCompress) {
		std::cout << "------------------------------------------------------------------------------------------------------\n";
		std::fstream input(file, std::ios_base::in | std::ios_base::binary);
		if (!input.is_open()) {
			std::cout << "Invalid file path!!\n";
			exit(1);
		}
		auto output = std::fstream(R"(..\RunLengthEncoding\testFile2.txt)", std::ios_base::out | std::ios_base::binary);
		std::cout << "compression started....\n";
		timer.Start();
		compressFile(input, output);
		timer.Stop();
		printf("\nFile compression complete\n");
		printf("RLE encoding time = %f seconds\n\n", timer.time());
		input.close();
		output.close();

		auto input1 = std::fstream(R"(..\RunLengthEncoding\testFile2.txt)", std::ios_base::in | std::ios_base::binary);
		std::fstream output1(R"(..\RunLengthEncoding\testFile3.txt)", std::ios_base::out | std::ios_base::binary);
		printf("Expansion started....\n");
		timer.Start();
		expandFile(input1, output1);
		timer.Stop();
		printf("\nFile expansion complete\n");
		printf("RLE decoding time = %f seconds\n\n", timer.time());
		input1.close();
		output1.close();

		//print file sizes

		std::cout << std::format("Original file size = {} bytes\n", fileSize(fs::path(file)));
		std::cout << std::format("Compressed file size = {} bytes\n", fileSize(fs::path(R"(..\RunLengthEncoding\testFile2.txt)")));
		std::cout << std::format("Expanded file size = {} bytes\n", fileSize(fs::path(R"(..\RunLengthEncoding\testFile3.txt)")));
		std::cout << std::format("compression efficiency of {} = {} \n\n", (file), (8 * fileSize(fs::path(R"(..\RunLengthEncoding\testFile2.txt)")))
			/ float(fileSize(fs::path(file))));
		std::cout << "------------------------------------------------------------------------------------------------------\n";
	}
}
