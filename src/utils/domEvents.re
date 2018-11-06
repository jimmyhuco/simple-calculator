[@bs.send]
external addEventListener: (Dom.document, string, 'evt => unit) => unit = "";

[@bs.send]
external removeEventListener: (Dom.document, string, 'evt => unit) => unit =
  "";

[@bs.val] external win: Dom.document = "window";