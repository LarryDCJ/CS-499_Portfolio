#include <fstream>
#include <sstream>
#include <iomanip>
#include "CSVparser.hpp"

namespace csv {
    Parser::Parser(const std::string &data, const DataType &type, char sep)
        : _type(type), _sep(sep) {
        std::string line;
        if (type == eFILE) {
            const std::string &file = data;
            std::ifstream ifile(file.c_str());

            if (ifile.is_open()) {
                while (ifile.good()) {
                    getline(ifile, line);
                    if (!line.empty())
                        _originalFile.push_back(line);
                }
                ifile.close();

                if (_originalFile.empty())
                    throw Error(std::string("No Data in ").append(_file));

                parseHeader();
                parseContent();
            } else {
                throw Error(std::string("Failed to open ").append(_file));
            }
        } else {
            std::istringstream stream(data);
            while (std::getline(stream, line))
                if (!line.empty())
                    _originalFile.push_back(line);
            if (_originalFile.empty())
                throw Error(std::string("No Data in pure content"));

            parseHeader();
            parseContent();
        }
    }

    Parser::~Parser() {
        for (auto &it: _content)
            delete it;
    }

    void Parser::parseHeader() {
        std::stringstream ss(_originalFile[0]);
        std::string item;

        while (std::getline(ss, item, _sep))
            _header.push_back(item);
    }

    void Parser::parseContent() {
        std::vector<std::string>::iterator it;

        it = _originalFile.begin();
        it++; // skip 0 line, the header

        for (; it != _originalFile.end(); it++) {
            bool quoted = false;
            int tokenStart = 0;
            unsigned int i = 0;

            auto *row = new Row(_header);

            for (; i != it->length(); i++) {
                if (it->at(i) == '"' && (i + 1 < it->length() && it->at(i + 1) == '"')) {
                    i++;
                } else if (it->at(i) == '"') {
                    quoted = ((!quoted));
                } else if (it->at(i) == ',' && !quoted) {
                    row->push(it->substr(tokenStart, i - tokenStart));
                    tokenStart = i + 1;
                }
            }

            //end
            row->push(it->substr(tokenStart, it->length() - tokenStart));

            // if value(s) missing
            if (row->size() != _header.size())
                throw Error("corrupted data !");
            _content.push_back(row);
        }
    }

    Row &Parser::getRow(unsigned int rowPosition) const {
        if (rowPosition < _content.size())
            return *(_content[rowPosition]);
        throw Error("can't return this row (doesn't exist)");
    }

    Row &Parser::operator[](unsigned int rowPosition) const {
        return Parser::getRow(rowPosition);
    }

    unsigned int Parser::rowCount() const {
        return _content.size();
    }

    unsigned int Parser::columnCount() const {
        return _header.size();
    }

    std::vector<std::string> Parser::getHeader() const {
        return _header;
    }

    std::string Parser::getHeaderElement(unsigned int pos) const {
        if (pos >= _header.size())
            throw Error("can't return this header (doesn't exist)");
        return _header[pos];
    }

    bool Parser::deleteRow(unsigned int pos) {
        if (pos < _content.size()) {
            delete *(_content.begin() + pos);
            _content.erase(_content.begin() + pos);
            return true;
        }
        return false;
    }

    bool Parser::addRow(unsigned int pos, const std::vector<std::string> &r) {
        auto *row = new Row(_header);

        for (const auto &it: r)
            row->push(it);

        if (pos <= _content.size()) {
            _content.insert(_content.begin() + pos, row);
            return true;
        }
        return false;
    }

    void Parser::sync() const {
        if (_type == DataType::eFILE) {
            std::ofstream f;
            f.open(_file, std::ios::out | std::ios::trunc);

            // header
            unsigned int i = 0;
            for (auto it = _header.begin(); it != _header.end(); it++) {
                f << *it;
                if (i < _header.size() - 1)
                    f << ",";
                else
                    f << std::endl;
                i++;
            }

            for (auto it: _content)
                f << *it << std::endl;
            f.close();
        }
    }

    const std::string &Parser::getFileName() const {
        return _file;
    }

    /*
    ** ROW
    */

    Row::Row(const std::vector<std::string> &header)
        : _header(header) {
    }

    Row::~Row() = default;

    unsigned int Row::size() const {
        return _values.size();
    }

    void Row::push(const std::string &value) {
        _values.push_back(value);
    }

    bool Row::set(const std::string &key, const std::string &value) {
        std::vector<std::string>::const_iterator it;
        int pos = 0;

        for (it = _header.begin(); it != _header.end(); it++) {
            if (key == *it) {
                _values[pos] = value;
                return true;
            }
            pos++;
        }
        return false;
    }

    std::string Row::operator[](unsigned int valuePosition) const {
        if (valuePosition < _values.size())
            return _values[valuePosition];
        throw Error("can't return this value (doesn't exist)");
    }

    std::string Row::operator[](const std::string &key) const {
        std::vector<std::string>::const_iterator it;
        int pos = 0;

        for (it = _header.begin(); it != _header.end(); it++) {
            if (key == *it)
                return _values[pos];
            pos++;
        }

        throw Error("can't return this value (doesn't exist)");
    }

    std::ostream &operator<<(std::ostream &os, const Row &row) {
        for (const auto &_value: row._values)
            os << _value << " | ";

        return os;
    }

    std::ofstream &operator<<(std::ofstream &os, const Row &row) {
        for (unsigned int i = 0; i != row._values.size(); i++) {
            os << row._values[i];
            if (i < row._values.size() - 1)
                os << ",";
        }
        return os;
    }
}
