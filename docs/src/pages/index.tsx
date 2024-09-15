import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import HomepageFeatures from '@site/src/components/HomepageFeatures';
import Heading from '@theme/Heading';

import styles from './index.module.css';

import { useState } from "react";
import { deltaCorpsPriest1 , useAsciiText } from "react-ascii-text";


export default function Home(): JSX.Element {
  const {siteConfig} = useDocusaurusContext();
  const [text, setText] = useState(["       CUBITRON", "     BALANCING", "          CUBE"]);
  const [isPaused, setIsPaused] = useState(false);

  const asciiTextRef = useAsciiText({
    animationCharacters: "▒░█",
    animationCharacterSpacing: 1,
    animationDelay: 2000,
    animationDirection: "down",
    animationInterval: 100,
    animationLoop: true,
    animationSpeed: 30,
    font: deltaCorpsPriest1,
    isPaused,
    text,
  });

  return (

<main className="container flex flex-col items-center justify-center min-h-screen">
  <article className="flex flex-col items-center justify-center text-s text-center">
    <pre className="text-white mx-auto text-center" ref={asciiTextRef} />
    <div className="container mt-8">
      <div className={styles.buttons}>
        <Link
          className="button button--secondary button--lg"
          to="/docs/intro">
          Read ⟶
        </Link>
      </div>
    </div>
  </article>
</main>
    // <main className="container bg-inherit mx-2 my-8 flex flex-col">
    //   <article className="text-s mx-auto text-center my-8">
    //     <pre className="text-white w-full mx-auto" ref={asciiTextRef} />
    //     <div className="container">
    //       <div className={styles.buttons}>
    //         <Link
    //           className="button button--secondary button--lg"
    //           to="/docs/intro">
    //           Read ⟶
    //         </Link>
    //       </div>
    //     </div>
    //   </article>
    // </main>
  );
}
