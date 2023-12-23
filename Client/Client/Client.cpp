//#define APP
#define UDPTEST
//#define UDPTEST2
//#define TCPTEST
//#define IMGPROCTEST
#ifdef APP
#include "ClientApp.h"
int main()
{
	ClientApp app;
	return app.main();
}
#endif
#ifdef IMGPROCTEST
#include <opencv2/opencv.hpp>
int main()
{
	{
		auto input{ cv::imread("D:\\Download\\362629304_935410660863688_7432816960704923792_n.jpg", cv::IMREAD_GRAYSCALE) };
		input = input * 1.4;
		cv::Mat equal, norm;
		cv::normalize(input, norm, 0, 255, cv::NORM_MINMAX);
		cv::equalizeHist(norm, equal);
		//double extremes[2];
		//cv::minMaxLoc(input, &extremes[0], &extremes[1]);
		//cv::minMaxLoc(output, &extremes[0], &extremes[1]);
	}
	{
		auto darkImage{ cv::imread("D:\\Download\\362629304_935410660863688_7432816960704923792_n.jpg", cv::IMREAD_GRAYSCALE) };
		// Increase brightness by adding a constant value (e.g., 50)
		int brightnessIncrease = 50;
		cv::Mat brightenedImage = darkImage + brightnessIncrease;

		// Apply histogram equalization to enhance overall contrast
		cv::Mat equalizedImage;
		cv::equalizeHist(brightenedImage, equalizedImage);

		// Apply adaptive histogram equalization to improve edges visibility
		cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
		clahe->setClipLimit(14); // Adjust the clip limit as needed (e.g., 4)
		cv::Mat enhancedEdgesImage, normalized;
		clahe->apply(equalizedImage, enhancedEdgesImage);
		cv::normalize(enhancedEdgesImage, normalized, 0, 255, cv::NORM_MINMAX);
	}
	{
		auto darkImage{ cv::imread("D:\\Download\\362629304_935410660863688_7432816960704923792_n.jpg", cv::IMREAD_GRAYSCALE) };
		// Increase brightness by applying a linear transform
		double alpha = 1.5; // Adjust brightness factor (1.0 means no change)
		cv::Mat brightenedImage = darkImage * alpha;

		// Apply adaptive histogram equalization with limited contrast enhancement
		cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
		cv::Mat enhancedEdgesImage;
		for (int i{ 1 }; i < 26; i += 2)
		{
			clahe->setClipLimit(i); // Adjust the clip limit as needed (e.g., 4)
			clahe->apply(brightenedImage, enhancedEdgesImage);
			int x = 10;
			x--;
		}
	}
	return 0;
}
#endif
#ifdef UDPTEST
#include <iostream>
#include <future>
#include <chrono>
#include <sstream>
#include <syncstream>
#include <asio.hpp>
#include <opencv2/opencv.hpp>

constexpr size_t CHUNK_SIZE = 65507;
asio::io_context io_context;
asio::ip::udp::resolver resolver(io_context);
auto endpoint = *resolver.resolve("127.0.0.1", "12345").begin();
using namespace std::chrono_literals;

void sendMatOverUDP() {
	try {
		asio::ip::udp::socket sender_socket(io_context);
		sender_socket.open(asio::ip::udp::v4());
		auto image{ cv::imread("D:\\Download\\362629304_935410660863688_7432816960704923792_n.jpg", cv::IMREAD_GRAYSCALE) };

		auto rows{ image.rows }, cols{ image.cols }, type{ image.type() };
		std::string header{std::format("{};{};{}", rows, cols, type)};
		auto size{ sender_socket.send_to(asio::buffer(header), endpoint) };
		std::vector<uchar> buffer;
		if (image.isContinuous())
			buffer.assign(image.data, image.data + image.total() * image.elemSize());
		else
			for (int i = 0; i < image.rows; ++i)
				buffer.insert(buffer.end(), image.ptr<uchar>(i), image.ptr<uchar>(i) + image.cols * image.channels());
		size_t numChunks = buffer.size() / CHUNK_SIZE;
		if (buffer.size() % CHUNK_SIZE != 0)
			numChunks++;

		std::this_thread::sleep_for(2ms);
		for (size_t i = 0; i < numChunks; ++i) {
			size_t offset = i * CHUNK_SIZE;
			size_t size = std::min(CHUNK_SIZE, buffer.size() - offset);
			sender_socket.send_to(asio::buffer(&buffer[offset], size), endpoint);
			std::this_thread::sleep_for(2ms);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception in sendMatOverUDP: " << e.what() << std::endl;
	}
}

cv::Mat receiveMatOverUDP() {
	try {
		asio::ip::udp::socket receiver_socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 12345));
		asio::ip::udp::endpoint sender_endpoint;
		std::string header(1024, '\0');
		size_t bytes_received = receiver_socket.receive_from(asio::buffer(header), sender_endpoint);
		std::vector<uchar> buffer;

		std::vector<std::vector<uchar>> chunks;
		while (true) {
			std::vector<uchar> chunk(CHUNK_SIZE);
			bytes_received = receiver_socket.receive_from(asio::buffer(chunk), sender_endpoint);
			chunks.emplace_back(std::move(chunk));
			if (bytes_received < CHUNK_SIZE)
				break;
		}

		std::array<int, 3> imageHeader;
		std::stringstream sstr(header);
		std::string tempValue;
		size_t index{ 0ull };
		while (std::getline(sstr, tempValue, ';'))
		{
			imageHeader[index] = std::stoi(tempValue);
			index++;
		}
		for (auto& currentChunk : chunks)
			buffer.insert(buffer.end(), currentChunk.begin(), currentChunk.end());
		return cv::Mat(imageHeader[0], imageHeader[1], imageHeader[2], buffer.data()).clone();
	}
	catch (std::exception& e) {
		std::cerr << "Exception in receiveMatOverUDP: " << e.what() << std::endl;
		return cv::Mat();
	}
}
int main() {
	try {
		std::thread senderThr{sendMatOverUDP};
		auto ftr{ std::async(std::launch::async,&receiveMatOverUDP) };
		if (auto receivedImage{ ftr.get() }; !receivedImage.empty()) {
			cv::imshow("Received Image", receivedImage);
			cv::waitKey(0);
		}
		else {
			std::cerr << "Failed to receive the image." << std::endl;
		}
		senderThr.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception in main: " << e.what() << std::endl;
	}

	return 0;
}
#endif 
#ifdef UDPTEST2
#include <iostream>
#include <asio.hpp>
#include <thread>

void sender(asio::io_context& io_context) {
	try {
		// Create a UDP socket
		asio::ip::udp::socket socket(io_context);

		// Resolve the destination endpoint
		asio::ip::udp::resolver resolver(io_context);
		asio::ip::udp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

		// Open the socket
		socket.open(asio::ip::udp::v4());

		// Data to be sent
		std::string message = "Hello, UDP Server!";

		// Send the data
		socket.send_to(asio::buffer(message), *endpoints.begin());

		std::cout << "Sent: " << message << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception in sender: " << e.what() << std::endl;
	}
}

void receiver(asio::io_context& io_context) {
	try {
		// Create a UDP socket
		asio::ip::udp::socket socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 12345));

		// Buffer to receive data
		std::array<char, 1024> buffer;

		// Receive data
		asio::ip::udp::endpoint sender_endpoint;
		size_t bytes_received = socket.receive_from(asio::buffer(buffer), sender_endpoint);

		// Print received data
		std::cout << "Received: " << std::string(buffer.data(), bytes_received) << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception in receiver: " << e.what() << std::endl;
	}
}

int main() {
	try {
		asio::io_context io_context;

		// Create separate threads for sender and receiver
		std::thread sender_thread(sender, std::ref(io_context));
		std::thread receiver_thread(receiver, std::ref(io_context));

		// Join the threads
		sender_thread.join();
		receiver_thread.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception in main: " << e.what() << std::endl;
	}

	return 0;
}
#endif 
#ifdef TCPTEST
#include <iostream>
#include <asio.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

void sendMatOverTCP(asio::ip::tcp::socket& socket, const cv::Mat& image) {
	try {
		// Convert cv::Mat to a byte array
		std::vector<uchar> buffer;
		if (image.isContinuous()) {
			buffer.assign(image.data, image.data + image.total() * image.elemSize());
		}
		else {
			for (int i = 0; i < image.rows; ++i) {
				buffer.insert(buffer.end(), image.ptr<uchar>(i), image.ptr<uchar>(i) + image.cols * image.channels());
			}
		}

		// Send the size of the data as a 64-bit integer first
		uint64_t dataSize = buffer.size();
		socket.send(asio::buffer(&dataSize, sizeof(dataSize)));

		// Send the byte array over TCP
		socket.send(asio::buffer(buffer));
	}
	catch (std::exception& e) {
		std::cerr << "Exception in sendMatOverTCP: " << e.what() << std::endl;
	}
}

cv::Mat receiveMatOverTCP(asio::ip::tcp::socket& socket) {
	try {
		// Receive the size of the data as a 64-bit integer first
		uint64_t dataSize = 0;
		socket.receive(asio::buffer(&dataSize, sizeof(dataSize)));

		// Receive the byte array over TCP
		std::vector<uchar> buffer(dataSize);
		socket.receive(asio::buffer(buffer));

		// Convert the received byte array back to cv::Mat
		return cv::Mat(1, dataSize, CV_8UC1, buffer.data()).clone();
	}
	catch (std::exception& e) {
		std::cerr << "Exception in receiveMatOverTCP: " << e.what() << std::endl;
		return cv::Mat();
	}
}

int main() {
	try {
		asio::io_context io_context;
		asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345));
		asio::ip::tcp::socket socket(io_context);

		// Wait for a client to connect
		acceptor.accept(socket);

		// Load an image using OpenCV
		cv::Mat image = cv::imread("D:\\Download\\362629304_935410660863688_7432816960704923792_n.jpg", cv::IMREAD_GRAYSCALE);
		if (image.empty()) {
			std::cerr << "Failed to load the image." << std::endl;
			return -1;
		}

		// Run the sender function in a separate thread
		std::thread sender_thread([&]() {
			sendMatOverTCP(socket, image);
			socket.close();
			});

		// Run the receiver function in the main thread
		cv::Mat receivedImage = receiveMatOverTCP(socket);
		socket.close();

		// Wait for the sender thread to finish
		sender_thread.join();

		if (!receivedImage.empty()) {
			// Display the received image
			cv::imshow("Received Image", receivedImage);
			cv::waitKey(0);
		}
		else {
			std::cerr << "Failed to receive the image." << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception in main: " << e.what() << std::endl;
	}

	return 0;
}
#endif