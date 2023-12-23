#pragma once
#include "Interfaces/IMoveDetectionResultExporter.h"
#include "Settings/UdpExporterSettings.h"
#include "Interfaces/IDetectionResultSerializer.h"
#include <asio.hpp>
#include <memory>
class UdpExporter :public IMoveDetectionResultExporter
{
public:
	UdpExporter(UdpExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer);
	bool ExportData(const MoveDetectionResult& dataToExport) override;
protected:
	constexpr static size_t CHUNK_SIZE = 65507;
	UdpExporterSettings _settings;
	asio::io_context _ioContext;
	std::unique_ptr<asio::ip::udp::socket> _pSocket;
	asio::ip::basic_resolver_entry<asio::ip::udp> _endpoint;
	std::string _serializationBuffer;
	std::unique_ptr<IDetectionResultSerializer> _pSerializer;
};