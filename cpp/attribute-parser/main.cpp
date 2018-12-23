// https://www.hackerrank.com/challenges/attribute-parser/problem
// recursive descent ftw

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <sstream>
#include <stack>

class Tag
{
public:
  Tag(std::string tag_name)
      : tag_name_m(std::move(tag_name))
  {
  }

  const std::string& name() const
  {
      return tag_name_m;
  }

  void add_attribute(const std::string& k, const std::string& v)
  {
      attributes_m[k] = std::move(v);
  }

  std::pair<bool, std::string> attribute(const std::string& k) const
  {
      if (attributes_m.find(k) == attributes_m.end())
      {
          return { false, "" };
      }

      return { true, attributes_m.at(k) };
  }

  void add_children(Tag tag)
  {
      children_m.emplace_back(tag);
  }

  const std::vector<Tag>& children() const
  {
      return children_m;
  }

private:
  std::string tag_name_m;
  std::map<std::string, std::string> attributes_m;

  std::vector<Tag> children_m;
};

enum class TokenType
{
    START,
    OPENING_TAG_BEGIN,
    CLOSING_TAG_BEGIN,
    TAG_END,
    NAME,
    VALUE,
    EQUAL_SIGN,
    END
};

class Tokenizer
{
public:
    Tokenizer(const std::string& input)
        :stream_m(input)
    {
        tokens_m.push(TokenValue{});
    }

    void next()
    {
        if (stream_m.eof())
        {
            TokenValue tv;
            tv.token_m = TokenType::END;
            tokens_m.emplace(std::move(tv));
            return;
        }

        int c = stream_m.get();
        while (c == ' ' || c == '\n' || c == '\t')
        {
            c = stream_m.get();
        }

        if (c == EOF)
        {
            TokenValue tv;
            tv.token_m = TokenType::END;
            tokens_m.emplace(std::move(tv));
        }
        else if (c == '<')
        {
            if (stream_m.peek() == '/')
            {
                (void)stream_m.get();
                TokenValue tv;
                tv.token_m = TokenType::CLOSING_TAG_BEGIN;
                tv.value_m = "</";
                tokens_m.emplace(std::move(tv));
            }
            else
            {
                TokenValue tv;
                tv.token_m = TokenType::OPENING_TAG_BEGIN;
                tv.value_m = "<";
                tokens_m.emplace(std::move(tv));
            }
        }
        else if (c == '>')
        {
            TokenValue tv;
            tv.token_m = TokenType::TAG_END;
            tv.value_m = ">";
            tokens_m.emplace(std::move(tv));
        }
        else if (c == '=')
        {
            TokenValue tv;
            tv.token_m = TokenType::EQUAL_SIGN;
            tv.value_m = "=";
            tokens_m.emplace(std::move(tv));
        }
        else if (c == '"')
        {
            TokenValue tv;
            tv.token_m = TokenType::VALUE;
            tv.value_m.clear();
            c = stream_m.get();
            while (c != '"')
            {
                tv.value_m.append(1, static_cast<char>(c));
                c = stream_m.get();
            }
            tokens_m.emplace(std::move(tv));
        }
        else
        {
            TokenValue tv;
            tv.token_m = TokenType::NAME;
            tv.value_m.clear();
            while (c != ' ' && c != '>')
            {
                tv.value_m.append(1, static_cast<char>(c));
                c = stream_m.get();
            }
            stream_m.putback(static_cast<char>(c));

            tokens_m.emplace(std::move(tv));
        }
    }

    const std::string& current_value()
    {
        return tokens_m.top().value_m;
    }
    TokenType current_token()
    {
        return tokens_m.top().token_m;
    }

    TokenType peek()
    {
        next();
        TokenType t = current_token();
        putback();
        tokens_m.pop();
        return t;
    }

    std::string get_rest_of_stream()
    {
        auto tellg = stream_m.tellg();
        if(tellg == -1)
        {
            tellg = static_cast<long>(stream_m.str().size());
        }
        return stream_m.str().substr(static_cast<size_t>(tellg));
    }

private:
    void putback()
    {
        std::string value = tokens_m.top().value_m;
        if(tokens_m.top().token_m == TokenType::VALUE)
        {
            value = "\"" + value + "\"";
        }
        stream_m = std::stringstream(value + get_rest_of_stream());
    }

    struct TokenValue
    {
        TokenType token_m{TokenType::START};
        std::string value_m;
    };
    std::stack<TokenValue> tokens_m;

    std::stringstream stream_m;
};

class Parser
{
public:
    Parser() = default;

    std::vector<Tag> parse(const std::string& input)
    {
        tokenizer_m = std::make_shared<Tokenizer>(input);

        std::vector<Tag> results;

        auto r = parse_tag();
        while (r.first)
        {
            results.emplace_back(r.second);
            r = parse_tag();
        }

        return results;
    }
private:
    // tag -> open-tag { tag } close-tag
    std::pair<bool, Tag> parse_tag()
    {
        const auto open_tag_pr = parse_open_tag();
        if(!open_tag_pr.first)
        {
            return {false, Tag{""}};
        }
        Tag result = make_tag(open_tag_pr.second);

        {
            auto child_pr = parse_tag();
            while(child_pr.first)
            {
                result.add_children(child_pr.second);
                child_pr = parse_tag();
            }
        }

        parse_close_tag(result.name());

        return {true, result};
    }

    struct OpenTag
    {
        std::string tag_name;
        std::map<std::string, std::string> attributes;
    };
    std::pair<bool, OpenTag> parse_open_tag()
    {
        OpenTag result{};

        const auto opening_token = tokenizer_m->peek();
        if(opening_token != TokenType::OPENING_TAG_BEGIN)
        {
            return {false, result};
        }

        tokenizer_m->next();
        assert(tokenizer_m->current_token() == TokenType::OPENING_TAG_BEGIN);

        tokenizer_m->next();
        assert(tokenizer_m->current_token() == TokenType::NAME);
        result.tag_name = tokenizer_m->current_value();

        tokenizer_m->next();
        while(tokenizer_m->current_token() == TokenType::NAME)
        {
            const auto attribute_name = tokenizer_m->current_value();

            tokenizer_m->next();
            assert(tokenizer_m->current_token() == TokenType::EQUAL_SIGN);

            tokenizer_m->next();
            assert(tokenizer_m->current_token() == TokenType::VALUE);
            const auto attribute_value = tokenizer_m->current_value();

            result.attributes[attribute_name] = attribute_value;

            tokenizer_m->next();
        }
        assert(tokenizer_m->current_token() == TokenType::TAG_END);
        return {true, result};
    }

    void parse_close_tag(const std::string& name)
    {
        tokenizer_m->next();
        assert(tokenizer_m->current_token() == TokenType::CLOSING_TAG_BEGIN);

        tokenizer_m->next();
        assert(tokenizer_m->current_token() == TokenType::NAME);
        const auto token_name = tokenizer_m->current_value();
        assert(token_name == name);

        tokenizer_m->next();
        assert(tokenizer_m->current_token() == TokenType::TAG_END);
    }

    Tag make_tag(const OpenTag& open_tag)
    {
        Tag result{open_tag.tag_name};
        for(const auto& entry : open_tag.attributes)
        {
            result.add_attribute(entry.first, entry.second);
        }
        return result;
    }

    std::shared_ptr<Tokenizer> tokenizer_m{};
};

// https://stackoverflow.com/a/7408245
std::vector<std::string> split(const std::string& text, const std::string& delims)
{
    std::vector<std::string> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while((end = text.find_first_of(delims, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if(start != std::string::npos)
        tokens.push_back(text.substr(start));

    return tokens;
}

std::string join(const std::vector<std::string>& parts, const std::string& delim)
{
    std::string result;
    if(parts.size() > 0)
    {
        result.append(parts[0]);
        for(size_t i=1;i<parts.size();i++)
        {
            result.append(delim);
            result.append(parts[i]);
        }
    }
    return result;
}

std::pair<bool, std::string> query(const std::vector<Tag>& tags, const std::string& query_str)
{
    auto query_parts = split(query_str, ".");
    if(query_parts.size() == 1)
    {
        query_parts = split(query_str, "~");
        for(const auto& tag : tags)
        {
            if(tag.name() == query_parts[0])
            {
                return tag.attribute(query_parts[1]);
            }
        }
        return {false, ""};
    }

    for(const auto& tag: tags)
    {
        if(tag.name() == query_parts[0])
        {
            query_parts.erase(query_parts.begin());
            return query(tag.children(), join(query_parts, "."));
        }
    }
    return {false, ""};
}

TEST_CASE("Tokenizing opening tag with attributes", "[tokenizer]")
{
    Tokenizer tokenizer{ R"(<tag1 value = "HelloWorld" value2 = "lol">)" };
    CHECK(tokenizer.current_token() == TokenType::START);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::OPENING_TAG_BEGIN);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::NAME);
    CHECK(tokenizer.current_value() == "tag1");
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::NAME);
    CHECK(tokenizer.current_value() == "value");
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::EQUAL_SIGN);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::VALUE);
    CHECK(tokenizer.current_value() == "HelloWorld");
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::NAME);
    CHECK(tokenizer.current_value() == "value2");
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::EQUAL_SIGN);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::VALUE);
    CHECK(tokenizer.current_value() == "lol");
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::TAG_END);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::END);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::END);
}

TEST_CASE("Tokenizing close tag", "[tokenizer]")
{
    Tokenizer tokenizer{ "</tag1>" };
    CHECK(tokenizer.current_token() == TokenType::START);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::CLOSING_TAG_BEGIN);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::NAME);
    CHECK(tokenizer.current_value() == "tag1");
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::TAG_END);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::END);
    tokenizer.next();
    CHECK(tokenizer.current_token() == TokenType::END);
}

TEST_CASE("Parsing tag with no attribute", "[parser]")
{
    Parser parser;
    std::string input_string{
        R"(<tag1>
        </tag1>)" };

    auto tags = parser.parse(input_string);
    REQUIRE(tags.size() == 1);

    Tag t = tags[0];
    {
        CHECK(t.name() == "tag1");
        CHECK(t.children().empty());
        auto q = t.attribute("bogus");
        CHECK(!q.first);
    }
}

TEST_CASE("Parsing tag with attribute", "[parser]")
{
    Parser parser;
    std::string input_string{
        R"(<tag1 value = "HelloWorld">
        </tag1>)" };
    auto tags = parser.parse(input_string);
    REQUIRE(tags.size() == 1);

    Tag t = tags[0];
    {
        CHECK(t.name() == "tag1");
        CHECK(t.children().empty());

        auto q = t.attribute("value");
        REQUIRE(q.first);
        CHECK(q.second == "HelloWorld");
        q = t.attribute("bogus");
        CHECK(!q.first);
    }
}

TEST_CASE("Parsing two tags", "[parser]")
{
    Parser parser;
    std::string input_string{
        R"(<tag1>
        </tag1>
        <tag2 value = "HelloWorld">
        </tag2>)" };

    auto tags = parser.parse(input_string);
    REQUIRE(tags.size() == 2);

    {
        Tag t = tags[0];
        {
            CHECK(t.name() == "tag1");
            CHECK(t.children().empty());
            auto q = t.attribute("bogus");
            CHECK(!q.first);
        }
    }
    {
        Tag t = tags[1];
        {
            CHECK(t.name() == "tag2");
            CHECK(t.children().empty());

            auto q = t.attribute("value");
            REQUIRE(q.first);
            CHECK(q.second == "HelloWorld");
            q = t.attribute("bogus");
            CHECK(!q.first);
        }
    }
}

TEST_CASE("Parsing nested tags", "[parser]")
{
    Parser parser;
    std::string input_string{
        R"(<tag1 value = "HelloWorld">
        <tag2 name = "Name1">
        </tag2>
        <tag3>
        </tag3>
        </tag1>)" };
    auto tags = parser.parse(input_string);
    REQUIRE(tags.size() == 1);

    Tag t = tags[0];
    {
        CHECK(t.name() == "tag1");

        auto q = t.attribute("value");
        CHECK(q.first);
        CHECK(q.second == "HelloWorld");
        q = t.attribute("bogus");
        CHECK(!q.first);
    }

    REQUIRE(t.children().size() == 2);
    {
        Tag tchild = t.children()[0];
        CHECK(tchild.name() == "tag2");
        CHECK(tchild.children().empty());
        auto qchild = t.attribute("bogus");
        CHECK(!qchild.first);
    }
    {
        Tag tchild = t.children()[1];
        CHECK(tchild.name() == "tag3");
        CHECK(tchild.children().empty());
        auto qchild = t.attribute("bogus");
        CHECK(!qchild.first);
    }
}

TEST_CASE("Test Query", "[query]")
{
    Parser parser;
    std::string input_string{
        R"(<tag1 value = "HelloWorld"><tag2 name = "Name1"></tag2></tag1>)" };
    auto tags = parser.parse(input_string);
    REQUIRE(tags.size() == 1);

    {
        auto r = query(tags, "tag1.tag2~name");
        CHECK(r.first);
        CHECK(r.second == "Name1");
    }
    {
        auto r = query(tags, "tag1~name");
        CHECK_FALSE(r.first);
    }
    {
        auto r = query(tags, "tag1~value");
        CHECK(r.first);
        CHECK(r.second == "HelloWorld");
    }
}
