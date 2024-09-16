import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import Heading from '@theme/Heading';

import logo from "@site/static/img/cubitron.svg";
import styles from './index.module.css';

// import { deltaCorpsPriest1 , useAsciiText } from "react-ascii-text";


export default function Home(): JSX.Element {
  const {siteConfig} = useDocusaurusContext();

  // const asciiTextRef = useAsciiText({
  //   animationCharacters: "▒░█",
  //   animationCharacterSpacing: 1,
  //   animationDelay: 2000,
  //   animationDirection: "down",
  //   animationInterval: 100,
  //   animationLoop: true,
  //   animationSpeed: 30,
  //   font: deltaCorpsPriest1,
  //   text: ["       CUBITRON", "     BALANCING", "          CUBE"]  
  // });

  return (
    <Layout>
    <main>
        <div className="container">
          <img src={logo} alt="" />
          <div className={styles.buttons}>
            <Link
              className="button button--secondary button--lg"
              to="/docs/intro">
              Read ⟶
            </Link>
          </div>
        </div>
    </main>
   </Layout>
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
