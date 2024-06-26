#pragma once
#include "Interfaces/IDetectionResultSerializer.h"
#include "Interfaces/IMoveDetectionResultExporter.h"
#include "Settings/UdpExporterSettings.h"
#include <asio.hpp>
#include <memory>
class UdpExporter :public IMoveDetectionResultExporter
{
public:
	UdpExporter(UdpExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer);
	void ExportData(const MoveDetectionResult& dataToExport) override;
protected:
	constexpr static size_t MAX_UDP_CHUNK_SIZE = 65507;
	UdpExporterSettings _settings;
	asio::io_context _ioContext;
	std::unique_ptr<asio::ip::udp::socket> _pSocket;
	asio::ip::basic_resolver_entry<asio::ip::udp> _endpoint;
	std::string _serializationBuffer;
	std::unique_ptr<IDetectionResultSerializer> _pSerializer;
};