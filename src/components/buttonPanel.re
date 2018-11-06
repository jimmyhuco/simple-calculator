open Esmodule;

import("./buttonPanel.css");

let component = ReasonReact.statelessComponent("ButtonPanel");

let make = (~onClick, ~flag, _children) => {
  ...component,
  render: _self =>
    <div className="component-button-panel">
      <div>
        <Button name=flag onClick />
        <Button name="+/-" onClick />
        <Button name="%" onClick />
        <Button name="/" str={j|÷|j} orange=true onClick />
      </div>
      <div>
        <Button name="7" onClick />
        <Button name="8" onClick />
        <Button name="9" onClick />
        <Button name="*" str="x" orange=true onClick />
      </div>
      <div>
        <Button name="4" onClick />
        <Button name="5" onClick />
        <Button name="6" onClick />
        <Button name="-" orange=true onClick />
      </div>
      <div>
        <Button name="1" onClick />
        <Button name="2" onClick />
        <Button name="3" onClick />
        <Button name="+" orange=true onClick />
      </div>
      <div>
        <Button name="0" wide=true onClick />
        <Button name="." onClick />
        <Button name="=" orange=true onClick />
      </div>
    </div>,
};