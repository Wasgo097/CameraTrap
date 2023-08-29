#include "UdpExporter.h"
#include <chrono>

using namespace std::chrono_literals;
UdpExporter::UdpExporter(UdpExporterSettings settings) :_settings{ std::move(settings) }
{
	asio::ip::udp::resolver resolver(_ioContext);
	_endpoint = *resolver.resolve(_settings.serverIp, _settings.serverPort).begin();
	_pSocket = std::make_unique<asio::ip::udp::socket>(_ioContext);
	_pSocket->open(asio::ip::udp::v4());
}

bool UdpExporter::ExportData(const MoveDetectionResult& dataToExport)
{
	_serializationBuffer = std::move(_serializer.Serialize(dataToExport));
	size_t numChunks{ _serializationBuffer.size() / CHUNK_SIZE };
	if (_serializationBuffer.size() % CHUNK_SIZE != 0)
		numChunks++;
	for (size_t i{ 0ull }; i < numChunks; ++i)
	{
		size_t offset{ i * CHUNK_SIZE };
		size_t size{ std::min(CHUNK_SIZE, _serializationBuffer.size() - offset) };
		_pSocket->send_to(asio::buffer(&_serializationBuffer[offset], size), _endpoint);
		std::this_thread::sleep_for(2ms);
	}
	return true;
}