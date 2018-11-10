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
        <Button name="/" txt={j|÷|j} otherCls="orange" onClick />
      </div>
      <div>
        <Button name="7" onClick />
        <Button name="8" onClick />
        <Button name="9" onClick />
        <Button name="*" txt="x" otherCls="orange" onClick />
      </div>
      <div>
        <Button name="4" onClick />
        <Button name="5" onClick />
        <Button name="6" onClick />
        <Button name="-" otherCls="orange" onClick />
      </div>
      <div>
        <Button name="1" onClick />
        <Button name="2" onClick />
        <Button name="3" onClick />
        <Button name="+" otherCls="orange" onClick />
      </div>
      <div>
        <Button name="0" otherCls="wide" onClick />
        <Button name="." onClick />
        <Button name="=" otherCls="orange" onClick />
      </div>
    </div>,
};