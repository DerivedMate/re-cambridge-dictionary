let ws = [%bs.raw
  {|
  (() => {
    let q
    if(/\?(.+)/.test(location.href)) {
      q = /\?(.+)/.exec(location.href)[1].split("&")
      .reduce((acc, x) => {
        const [k, v] = x.split("=")
        acc[k] = v
        return acc
      }, {})
    }
    return q && q['words'] ? q['words'] : []
  })()
|}
];

let re = [%bs.re "/\?words=(.+&?)/"];

let words =
  switch (Helpers.URL.href |> Js.String.match(re)) {
  | Some(res) => res[1] |> Helpers.URL.decodeURI
  | None => ""
  }

ReactDOMRe.renderToElementWithId(<App initialWords=words />, "root");