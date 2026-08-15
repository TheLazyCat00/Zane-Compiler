(* Parsing the checked-in sample is the common case while the front end is the
   only stage, so it stays the default when no source is named. *)
let default_path = "test-parser/main.zn"

let read_file path =
  try In_channel.with_open_text path In_channel.input_all with
  | Sys_error message ->
      prerr_endline message;
      exit 2

(* The name reported in parse errors travels with the text, so reading from
   standard input still produces a located message. *)
let source () =
  match Sys.argv with
  | [| _ |] -> (default_path, read_file default_path)
  | [| _; "-" |] -> ("<stdin>", In_channel.input_all In_channel.stdin)
  | [| _; path |] -> (path, read_file path)
  | _ ->
      prerr_endline "usage: compiler [SOURCE|-]";
      exit 2

let () =
  let filename, input = source () in
  match Cst.parse filename input with
  | Ok cst ->
      let output = Cst.to_node cst in
      print_string (Tree_graph.render output)
  | Error message ->
      prerr_string message;
      exit 1
