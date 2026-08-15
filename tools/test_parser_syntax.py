#!/usr/bin/env python3
import subprocess
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
PARSER_ACCEPT = ROOT / "_build" / "default" / "tools" / "parser_accept.exe"


class ParserSyntaxTests(unittest.TestCase):
    def setUp(self) -> None:
        if not PARSER_ACCEPT.exists():
            self.skipTest("requires built parser_accept executable")

    def assert_parses(self, source: str) -> None:
        parsed = subprocess.run(
            [str(PARSER_ACCEPT), source],
            text=True,
            capture_output=True,
            timeout=30,
        )
        self.assertEqual(parsed.returncode, 0, parsed.stdout + parsed.stderr)

    def test_named_field_and_implicit_constructors(self) -> None:
        self.assert_parses(
            '''
            type Vector2 = struct { x Float; y Float; }

            Vector2.zeros() => init{x = Float(0), y = Float(0)};
            Vector2.fromPair{x Float, y Float = Float(0)} => init{x, y};
            Vector2<T>{x T Type, y T} => init{x, y};
            implicit Vector2(v Float) => init{x = v, y = v};

            Unit use() {
                a Vector2.zeros();
                b Vector2{x = Float(1), y = Float(2)};
                c Vector2.fromPair{x = Float(3)};
                return Unit();
            }
            '''
        )

    def test_guest_types_subscripts_assignment_guard_and_spawn(self) -> None:
        self.assert_parses(
            '''
            type Node = #struct { next &Node; }

            (this Node)[index Int] => this;

            Unit work(this Node) mut {
                this.next = &this;
                guard true;
                guard true { std$print("ok"); }
                spawn run();
                return Unit();
            }
            '''
        )

    def test_match_enum_map_type_members_pipe_and_inequality(self) -> None:
        self.assert_parses(
            '''
            package demo;
            import std;

            type Color = enum [ red, green ]
            Color.label String [ red = "Red", green = "Green" ];

            String show(c Color) => match c {
                red => Color.red.label;
                green => "Green";
            };

            Unit use() {
                different Bool = true ~= false;
                label String = show|Color.red;
                rendered String = Color.red:render|label;
                first String = label[0];
                return Unit();
            }
            '''
        )

    def test_match_arm_terminator_follows_the_body_shape(self) -> None:
        self.assert_parses(
            '''
            type Color = enum [ red, green ]

            String show(c Color) {
                label String = match c {
                    red {
                        return "Red";
                    }
                    green => "Green";
                };
                return label;
            }
            '''
        )

    def test_alias_moulds_and_line_comments(self) -> None:
        self.assert_parses(
            '''
            // aliases may use the same mould RHS as type declarations
            alias Pair = struct { left Int; right Int; }
            /// documentation comments are accepted lexically
            type Wrapped = struct { pair Pair; }
            '''
        )

    def test_generic_parameter_introduction_and_collection_literals(self) -> None:
        self.assert_parses(
            '''
            type Buffer<T Type, n Number> = struct {
                data Array<T, n>;
            }

            T first(values Array<T Type, n Number>) => values[0];

            Unit literals() {
                values Array<Int, 3> = Array([Int(1), Int(2), Int(3)]);
                return Unit();
            }
            '''
        )


if __name__ == "__main__":
    unittest.main()
