#pragma once
#include "Interfaces/IMoveDetectionResultExporter.h"
#include "Settings/UdpExporterSettings.h"
#include <asio.hpp>
class UdpExporter :public IMoveDetectionResultExporter
{
public:
	UdpExporter(UdpExporterSettings settings);
	bool ExportData(const MoveDetectionResult& dataToExport) override;
protected:
	constexpr static size_t CHUNK_SIZE = 65507;
	UdpExporterSettings _settings;
	asio::io_context _ioContext;
	//asio::ip::udp::socket _socket;
	asio::ip::basic_resolver_entry<asio::ip::udp> _endpoint;
};